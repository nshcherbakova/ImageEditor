# This Python file uses the following encoding: utf-8
#import sys
#from PySide6.QtWidgets import QApplication
from http.server import BaseHTTPRequestHandler, HTTPServer
from http import client as HTTPStatus
from pathlib import Path

import re
import shutil
import json

class ImageServerRequestHandler(BaseHTTPRequestHandler):
    #          BaseHTTPRequestHandler methods

    def do_GET(self):
        print("\n GET PATH " + self.path)

        if  self.path.endswith(".jpg"):
            self.get_image()
        elif self.path.endswith("all_image_list"):
            self.get_image_list()
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
        self.send_response(HTTPStatus.OK)
        self.send_header('Content-type', 'image/jpg')
        self.end_headers()

        path = self.path
        with open("data/images"+ path, 'rb') as content:
            shutil.copyfileobj(content, self.wfile)
        return

    # process pages request
    def get_page(self):
        self.send_response(HTTPStatus.OK)
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

    def get_image_list(self):
        self.send_response(HTTPStatus.OK)
        self.send_header('Content-type','application/json')
        self.end_headers()

        images = Path("data/images/").glob("*.jpg")
        image_strings = [p.name for p in images]
        print("Images: ")
        print(image_strings)

        message = json.dumps(image_strings)
        print(message)

        self.wfile.write(bytes(message, "utf8"))

server = HTTPServer(('127.0.0.1', 8081), ImageServerRequestHandler)

try:
    print("Run Image Server")
    server.serve_forever()
except KeyboardInterrupt:
    pass

#if __name__ == "__main__":
#    app = QApplication(sys.argv)
    # ...
#    sys.exit(app.exec())
