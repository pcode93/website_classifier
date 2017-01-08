# -*- coding: utf-8 -*-

from bs4 import BeautifulSoup
import urllib2

def get_text(url):
    html = BeautifulSoup(urllib2.urlopen(url).read(), 'html.parser')

    for resource in html(['script', 'style']):
        resource.decompose()
    return html.get_text().encode('utf-8')

if __name__ == '__main__':
    for word in get_text("http://google.com").split():
        print word
