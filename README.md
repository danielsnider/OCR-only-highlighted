OCR only highlighted text
==================

Amazon's Kindle iOS app allows text to be highlighted, but restricts copy and pasting. This algorithm performs OCR only on text that has been highlighted.

Demo @ my online portfolio: [http://challengeaccepted.me/](http://challengeaccepted.me/)

##Dependencies
- [OpenCV](http://opencv.willowgarage.com/wiki/InstallGuide%20%3A%20Debian)
- [tessarct-ocr](http://code.google.com/p/tesseract-ocr/) (with english tessdata package)
- c++ compiler

Install
-------
Linux:

    git clone git@github.com:danielsnider/OCR-only-highlighted.git
    cd OCR-only-highlighted
    chmod +x ./build.sh
    ./build.sh

Usage
-----
    ./highlight_OCR.out [image] [colour of highlighted colour, red intensity] [green intensity] [blue intensity]
  
Notes
-----
A common iOS kindle highlight colour is (251,226,152).
Also, Amazon offers a "Your Highlights" section on their website. That may be an easier way to select and copy paste text than this project. 
