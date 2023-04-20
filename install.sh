#!/bin/bash

# Downloading libs
curl -LOsS https://komiyak-s3.s3.us-west-2.amazonaws.com/cqNJtk7L0XVD8kIV8SbE0BES7Gt0PRYox81kfggsFeT0PzZ37WeGOFrvhzS352ut/glfw-3.3.8.zip
curl -LOsS https://komiyak-s3.s3.us-west-2.amazonaws.com/cqNJtk7L0XVD8kIV8SbE0BES7Gt0PRYox81kfggsFeT0PzZ37WeGOFrvhzS352ut/glad.zip

# Unzipping and installing them
unzip glfw-3.3.8.zip -d glfw_wrap
unzip glad.zip -d glfw_wrap/glad-opengl-version-4-6

# Cleaning up zips
rm glfw-3.3.8.zip
rm glad.zip
