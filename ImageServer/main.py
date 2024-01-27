# This Python file uses the following encoding: utf-8
#import sys
#from PySide6.QtWidgets import QApplication
from http.server import BaseHTTPRequestHandler, HTTPServer
from http import client as HTTPStatus
from pathlib import Path

from requests_toolbelt.multipart import decoder


import shutil
import json
import uuid
import sys

class ImageServerRequestHandler(BaseHTTPRequestHandler):
    #          BaseHTTPRequestHandler methods

    IMAGE_EXTENSION = ".jpg"
    CONTENT_TYPE = 'image/jpg';
    SERVER_ALL_IMAGES_PATH = "all_image_list"
    FILE_DATA_PATH = "data"
    FILE_IMAGE_DATA_PATH = "data/images"

    def do_GET(self):
        print("\n GET PATH " + self.path)

        if  self.path.endswith(self.IMAGE_EXTENSION):
            self.get_image()
        elif self.path.endswith(self.SERVER_ALL_IMAGES_PATH):
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

        self.save_image(image_byte);

        self.send_response(HTTPStatus.OK)
        self.send_header('Content-Type', 'text/html')
        self.end_headers()

        return


    #          ImageServerRequestHandler methods

    # process images request
    def get_image(self):
        self.send_response(HTTPStatus.OK)
        self.send_header('Content-type', self.CONTENT_TYPE)
        self.end_headers()

        path = self.path
        with open(self.FILE_IMAGE_DATA_PATH + path, 'rb') as content:
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
            file  = open(self.FILE_DATA_PATH+ path + ".html", 'r')
        except FileNotFoundError:
            file  = open(self.FILE_DATA_PATH +"/404.html", 'r')

        message = file.read()
        file.close()
        self.wfile.write(bytes(message, "utf8"))
        return

    def get_image_list(self):
        self.send_response(HTTPStatus.OK)
        self.send_header('Content-type','application/json')
        self.end_headers()

        images = Path(self.FILE_IMAGE_DATA_PATH).glob("*.jpg")
        image_strings = [p.name for p in images]
        print("Images: ")
        print(image_strings)

        message = json.dumps(image_strings)
        print(message)

        self.wfile.write(bytes(message, "utf8"))

        return

    def save_image(self, image_byte):

        path = Path(self.FILE_IMAGE_DATA_PATH + "/" + self.generate_uniq_file_name() + ".jpg")

        with open(path, "wb") as dst:
           dst.write(image_byte)

        return

    def generate_uniq_file_name(self):
        return uuid.uuid4().hex;

host = '127.0.0.1'
port = 8081
if(len(sys.argv) == 3):
    host = str(sys.argv[1])
    port = int(sys.argv[2])

server = HTTPServer((host, port), ImageServerRequestHandler)

try:
    print("Run Image Server")
    server.serve_forever()
except KeyboardInterrupt:
    pass

