FROM ubuntu:12.04

WORKDIR /workdir

# Change the default shell to bash
SHELL ["/bin/bash", "-c"]

# Curl command from https://unix.stackexchange.com/a/421318/14436
RUN echo -e 'function __curl() { \n  read proto server path <<<$(echo ${1//// }) \n  DOC=/${path// //} \n  HOST=${server//:*} \n  PORT=${server//*:} \n  [[ x"${HOST}" == x"${PORT}" ]] && PORT=80 \n  exec 3<>/dev/tcp/${HOST}/$PORT \n  echo -en "GET ${DOC} HTTP/1.0\\r\\nHost: ${HOST}\\r\\n\\r\\n" >&3 \n  (while read line; do \n   [[ "$line" == $'"'"'\\r'"'"' ]] && break \n  done && cat) <&3 \n  exec 3>&- \n}' > curl.sh

RUN source curl.sh && \
  __curl http://launchpadlibrarian.net/102057931/gcc-4.6-base_4.6.3-1ubuntu5_i386.deb > gcc-4.6-base_4.6.3-1ubuntu5_i386.deb && \
  __curl http://launchpadlibrarian.net/102057944/cpp-4.6_4.6.3-1ubuntu5_i386.deb > cpp-4.6_4.6.3-1ubuntu5_i386.deb && \
  __curl http://launchpadlibrarian.net/95985360/binutils_2.22-6ubuntu1_i386.deb > binutils_2.22-6ubuntu1_i386.deb && \
  __curl http://launchpadlibrarian.net/102057932/libgcc1_4.6.3-1ubuntu5_i386.deb > libgcc1_4.6.3-1ubuntu5_i386.deb && \
  __curl http://launchpadlibrarian.net/102057940/libgomp1_4.6.3-1ubuntu5_i386.deb > libgomp1_4.6.3-1ubuntu5_i386.deb && \
  __curl http://launchpadlibrarian.net/102057936/libquadmath0_4.6.3-1ubuntu5_i386.deb > libquadmath0_4.6.3-1ubuntu5_i386.deb && \
  __curl http://launchpadlibrarian.net/312075351/libc6_2.15-0ubuntu10.18_i386.deb > libc6_2.15-0ubuntu10.18_i386.deb && \
  __curl http://launchpadlibrarian.net/87459549/libgmp10_5.0.2+dfsg-2ubuntu1_i386.deb > libgmp10_5.0.2+dfsg-2ubuntu1_i386.deb && \
  __curl http://launchpadlibrarian.net/83179070/libmpc2_0.9-4_i386.deb > libmpc2_0.9-4_i386.deb && \
  __curl http://launchpadlibrarian.net/99920413/libmpfr4_3.1.0-3ubuntu1_i386.deb > libmpfr4_3.1.0-3ubuntu1_i386.deb && \
  __curl http://launchpadlibrarian.net/84865068/zlib1g_1.2.3.4.dfsg-3ubuntu4_i386.deb > zlib1g_1.2.3.4.dfsg-3ubuntu4_i386.deb && \
  __curl http://launchpadlibrarian.net/102057961/libstdc++6_4.6.3-1ubuntu5_i386.deb > libstdc++6_4.6.3-1ubuntu5_i386.deb && \
  __curl http://launchpadlibrarian.net/102057975/gcc-4.6_4.6.3-1ubuntu5_i386.deb > gcc-4.6_4.6.3-1ubuntu5_i386.deb

RUN dpkg -i *.deb
