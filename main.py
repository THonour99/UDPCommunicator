import socket
import time
import threading
import sys
import datetime
import os


class UDPServer:
    def __init__(self, host='0.0.0.0', port=8888, log_file=None):
        self.host = host
        self.port = port
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.running = False
        self.clients = set()  # 记录客户端地址

        # 配置日志文件
        self.log_file = log_file
        if self.log_file:
            log_dir = os.path.dirname(self.log_file)
            if log_dir and not os.path.exists(log_dir):
                os.makedirs(log_dir)

    def log(self, message):
        """记录日志消息，输出到控制台和文件"""
        timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        log_message = f"[{timestamp}] {message}"

        # 输出到控制台
        print(log_message)

        # 输出到文件
        if self.log_file:
            try:
                with open(self.log_file, 'a', encoding='utf-8') as f:
                    f.write(log_message + '\n')
            except Exception as e:
                print(f"写入日志文件失败: {e}")

    def start(self):
        """启动UDP服务器"""
        try:
            # 绑定套接字
            self.socket.bind((self.host, self.port))
            self.running = True

            # 启动接收消息的线程
            self.receive_thread = threading.Thread(target=self.receive_messages)
            self.receive_thread.daemon = True
            self.receive_thread.start()

            self.log(f"UDP服务器已在 {self.host}:{self.port} 启动")

            # 主线程循环，用于处理控制台输入
            try:
                while self.running:
                    # 支持在控制台输入命令
                    command = input("输入'quit'退出服务器, 'clients'查看客户端列表, 'broadcast 消息'广播消息: ")
                    if command.lower() == 'quit':
                        self.stop()
                        break
                    elif command.lower() == 'clients':
                        if not self.clients:
                            self.log("没有已连接的客户端")
                        else:
                            self.log("已连接的客户端:")
                            for i, client in enumerate(self.clients, 1):
                                self.log(f"{i}. {client[0]}:{client[1]}")
                    elif command.lower().startswith('broadcast '):
                        message = command[10:]  # 提取broadcast后的消息内容
                        self.broadcast_message(message)
                    else:
                        self.log("未知命令")
            except KeyboardInterrupt:
                self.stop()

        except Exception as e:
            self.log(f"服务器启动失败: {e}")
            self.stop()

    def stop(self):
        """停止UDP服务器"""
        if self.running:
            self.running = False
            self.socket.close()
            self.log("UDP服务器已停止")

    def receive_messages(self):
        """接收并处理UDP消息"""
        while self.running:
            try:
                data, addr = self.socket.recvfrom(1024)
                message = data.decode('utf-8')

                self.log(f"收到来自 {addr[0]}:{addr[1]} 的消息: {message}")

                # 处理连接测试消息
                if message == "CONNECTION_TEST":
                    response = "CONNECTION_CONFIRMED"
                    self.send_message(response, addr)
                    self.clients.add(addr)  # 记录客户端地址
                    self.log(f"确认来自 {addr[0]}:{addr[1]} 的连接测试")
                    continue

                # 记录客户端地址(如果不存在)
                if addr not in self.clients:
                    self.clients.add(addr)
                    self.log(f"新客户端连接: {addr[0]}:{addr[1]}")

                # 回复消息
                response = f"服务器已收到: {message}"
                self.send_message(response, addr)

                # 广播给其他客户端
                self.broadcast_message(f"用户 {addr[0]}:{addr[1]} 说: {message}", exclude=addr)

            except Exception as e:
                if self.running:  # 仅在服务器还在运行时记录错误
                    self.log(f"接收消息时出错: {e}")

    def send_message(self, message, addr):
        """发送消息到指定地址"""
        try:
            self.socket.sendto(message.encode('utf-8'), addr)
        except Exception as e:
            self.log(f"发送消息到 {addr[0]}:{addr[1]} 失败: {e}")
            # 如果发送失败，可能客户端已断开，从列表中移除
            if addr in self.clients:
                self.clients.remove(addr)
                self.log(f"客户端 {addr[0]}:{addr[1]} 已从列表中移除")

    def broadcast_message(self, message, exclude=None):
        """广播消息给所有客户端，可选排除指定客户端"""
        if not self.clients:
            self.log("没有客户端可接收广播消息")
            return

        self.log(f"广播消息: {message}")
        for client in list(self.clients):  # 使用列表复制，因为可能在循环中修改集合
            if exclude and client == exclude:
                continue
            try:
                self.socket.sendto(f"广播: {message}".encode('utf-8'), client)
            except Exception as e:
                self.log(f"广播消息到 {client[0]}:{client[1]} 失败: {e}")
                if client in self.clients:
                    self.clients.remove(client)
                    self.log(f"客户端 {client[0]}:{client[1]} 已从列表中移除")


def main():
    # 获取命令行参数
    port = 8888
    if len(sys.argv) > 1:
        try:
            port = int(sys.argv[1])
        except ValueError:
            print(f"无效的端口号: {sys.argv[1]}，使用默认端口8888")

    # 创建并启动服务器
    log_file = os.path.join(os.path.dirname(os.path.abspath(__file__)), "udp_server_log.txt")
    server = UDPServer(port=port, log_file=log_file)

    try:
        server.start()
    except Exception as e:
        print(f"服务器运行时出错: {e}")
    finally:
        # 确保服务器停止
        if hasattr(server, 'running') and server.running:
            server.stop()


if __name__ == "__main__":
    main()