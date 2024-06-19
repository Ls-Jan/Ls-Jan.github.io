#如果直接使用python -m http.server启动本地服务器的话会出现一个问题就是MIME错误，
#不懂网页前端开发，也不怎么想动Vue项目的配置，因为打出来的项目挂在github.io主页是能正常使用的，所以怎么都感觉不该是Vue项目配置的问题，
#然后我半懂不懂地去搜本地服务器如何携带MIME信息，于是找到这份代码。
#源码：https://dev.to/gavi/custom-mime-type-with-python-3-httpserver-530l


# Set the server address and port
server_address = ("localhost", 8000)
print(f"Serving on http://{server_address[0]}:{server_address[1]}")

# 【打开网页】
if True:
	import os
	os.system(f'explorer http://{server_address[0]}:{server_address[1]}')



import http.server
import socketserver
from urllib.parse import urlparse

# Define the custom MIME types
custom_mime_types = {
    ".js": "text/javascript",
	# ".wgsl": "text/javascript",
    # Add more custom MIME types here as needed
}

class CustomMimeTypesHTTPRequestHandler(http.server.SimpleHTTPRequestHandler):
    def guess_type(self, path):
        url = urlparse(path)
        file_ext = url.path
        pos = file_ext.rfind('.')
        if pos != -1:
            file_ext = file_ext[pos:]
        else:
            file_ext = ""

        # Check if the file extension has a custom MIME type
        if file_ext in custom_mime_types:
            return custom_mime_types[file_ext]

        # Fallback to the default MIME type guessing
        return super().guess_type(path)

# Set the handler to use the custom class
handler = CustomMimeTypesHTTPRequestHandler
# Create the server and bind the address and handler
httpd = socketserver.TCPServer(server_address, handler)
httpd.serve_forever()


