import http.server

class RedirectHandler(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(301)
        self.send_header("location","http://www.google.com") #place a url that you want, you can use this to bypass internal restriction
        #use it with - $ngrok http 8000
        self.end_headers()

def run(server_class=http.server.HTTPServer, handler_class=RedirectHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()


if __name__ == '__main__':
    run()