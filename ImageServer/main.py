# This Python file uses the following encoding: utf-8
#import sys
#from PySide6.QtWidgets import QApplication
from http.server import BaseHTTPRequestHandler, HTTPServer
import re
import shutil


class ImageServerRequestHandler(BaseHTTPRequestHandler):
    #          BaseHTTPRequestHandler methods

    def do_GET(self):
        if  self.path.endswith(".jpg"):
            self.get_image()
        else :
            self.get_page()
        return

    def do_POST(self):
        self.send_response(301)
        self.send_header('Location','/support')
        self.end_headers()
        path = self.path
        #Обработчик подписки
        if path == "/email":
            content_len = int(self.headers.get('Content-Length'))
            post = self.rfile.read(content_len)
            email = re.split(r"email=",str(post))[1]
            email = re.sub(r"\'","",email)
            print(email)
        return

    #          ImageServerRequestHandler methods

    # process images request
    def get_image(self):
        self.send_response(200)
        self.send_header('Content-type', 'image/jpg')
        self.end_headers()

        path = self.path
        with open("data/images"+ path, 'rb') as content:
            shutil.copyfileobj(content, self.wfile)
        return

    # process pages request
    def get_page(self):
        self.send_response(200)
        self.send_header('Content-type','text/html')
        self.end_headers()


        path = self.path
        if path == "/":
            path = "/index"

        try:
            file  = open("data"+ path + ".html", 'r')
        except FileNotFoundError:
            file  = open("data/404.html", 'r')

        message = file.read()
        file.close()
        self.wfile.write(bytes(message, "utf8"))
        return

server = HTTPServer(('127.0.0.1', 8081), ImageServerRequestHandler)

try:
    server.serve_forever()
except KeyboardInterrupt:
    pass

#if __name__ == "__main__":
#    app = QApplication(sys.argv)
    # ...
#    sys.exit(app.exec())
