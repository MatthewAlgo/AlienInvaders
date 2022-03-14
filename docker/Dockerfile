FROM dorowu/ubuntu-desktop-lxde-vnc:bionic-lxqt

COPY install_deps.sh /home/sandbox/install_deps.sh

# Add a docker user
  # RUN groupadd -g 1000 docker
  # RUN useradd -d /home/docker -s /bin/bash -m docker -u 1000 -g 1000
  # RUN echo "docker:docker" | chpasswd && adduser docker sudo

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ COMMANDS ~~~~~~~~~

############ Other
# BUILD DOCKER IMAGE:
  # docker build -t docker-xterm .

# RUN DOCKER IMAGE:
  # docker run --rm -p 5800:5800 -p 5900:5900 docker-xterm
