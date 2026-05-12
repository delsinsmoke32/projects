from urllib.request import urlopen

url = "http://olympus.realpython.org/profiles/aphrodite"
page = urlopen(url)
html_bytes = page.read()
html = html_bytes.decode("utf-8")
title = html.find("<title>") #returna indice
start_title = title + len("<title>")
end_title = html.find("</title>")

print(html[start_title:end_title])
print(html)