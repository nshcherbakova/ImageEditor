FROM python:3
RUN mkdir ImageServer
RUN cd ImageServer
COPY main.py main.py
COPY docker/requirements.txt requirements.txt
RUN pip3 install -r requirements.txt
EXPOSE 8081
ENTRYPOINT ["python3", "main.py", "http://ie.antonsh.me/" , "81"]
