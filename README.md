# imbue
I wanted to learn about stenography, so here we are.
## Build
```
make
```
## JPG Stenography
#### Embed a file inside a jpg image.
##### Generate image from scratch:
This option will generate a jpg file from scratch using your file input as image data. Data is injected between the 0xFF 0xDA and 0xFF 0xD9 markers of an empty jpg file to create your image.

`./imbue -jpg FILE_TO_INJECT` Generate jpg with an image size automatically calculated to fit your data.
