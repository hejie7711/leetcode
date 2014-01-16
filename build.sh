#!/bin/bash
rm -rf _site
jekyll build -s ./jekyll/
cp -r ./_site/* .
