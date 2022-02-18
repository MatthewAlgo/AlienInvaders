FROM debian:latest

RUN apt-get update
RUN apt-get install -y firefox-esr
RUN groupadd -g 1000 lyonn
RUN useradd -d /home/matthewalgo -s /bin/bash -m matthewalgo -u 1000 -g 1000
USER matthewalgo
ENV HOME /home/matthewalgo

RUN apt install git
RUN git clone https://github.com/MatthewAlgo/AlienInvadersRetroBuild.git

CMD /usr/bin/firefox