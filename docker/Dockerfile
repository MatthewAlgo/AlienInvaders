FROM jlesage/baseimage-gui:debian-11

RUN apt-get update
RUN add-pkg xterm
RUN add-pkg sudo
RUN add-pkg git

# RUN apt-get install git
RUN groupadd -g 1000 docker
RUN useradd -d /home/docker -s /bin/bash -m docker -u 1000 -g 1000
RUN echo "docker:docker" | chpasswd && adduser docker sudo

# RUN git clone https://github.com/MatthewAlgo/AlienInvadersRetroBuild.git

# Copy the start script.
COPY startapp.sh /startapp.sh

# Set the name of the application.
ENV APP_NAME="Terminal"

# USER docker
# ENV HOME /home/docker

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ COMMANDS ~~~~~~~~~


# REMOVE ALL DOCKER CONTAINERS:
# docker container stop $(docker container ls -aq) && docker system prune -af --volumes

# REMOVE ALL DOCKER IMAGES:
# docker rmi $(docker images -a -q)

# BUILD DOCKER IMAGE:
# docker build -t docker-xterm .

# RUN DOCKER IMAGE:
# docker run --rm -p 5800:5800 -p 5900:5900 docker-xterm