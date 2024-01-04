# This Python file uses the following encoding: utf-8
#import sys
#from PySide6.QtWidgets import QApplication
from http.server import BaseHTTPRequestHandler, HTTPServer
from http import client as HTTPStatus
from pathlib import Path

import re
import shutil
import json
from requests_toolbelt.multipart import decoder

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
        print("POST image")
        content_length = int(self.headers['Content-Length'])
        file_content = self.rfile.read(content_length)

        multipart_data = decoder.MultipartDecoder(file_content, self.headers['Content-Type']).parts
        image_byte = multipart_data[0].content

        path = Path("data/images/image4.jpg")
        with open(path, "wb") as dst:
           dst.write(image_byte)

        self.send_response(HTTPStatus.OK)
        self.send_header('Content-Type', 'text/html')
        self.end_headers()


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
