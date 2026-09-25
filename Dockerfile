FROM ubuntu:12.04

WORKDIR /workdir

# Change the default shell to bash
SHELL ["/bin/bash", "-c"]

# Curl command from https://unix.stackexchange.com/a/421318/14436
RUN echo -e 'function __curl() { \n  read proto server path <<<$(echo ${1//// }) \n  DOC=/${path// //} \n  HOST=${server//:*} \n  PORT=${server//*:} \n  [[ x"${HOST}" == x"${PORT}" ]] && PORT=80 \n  exec 3<>/dev/tcp/${HOST}/$PORT \n  echo -en "GET ${DOC} HTTP/1.0\\r\\nHost: ${HOST}\\r\\n\\r\\n" >&3 \n  (while read line; do \n   [[ "$line" == $'"'"'\\r'"'"' ]] && break \n  done && cat) <&3 \n  exec 3>&- \n}' > curl.sh

ENV DEBIAN_FRONTEND=noninteractive

# We need curl for HTTPS
RUN source curl.sh && \
  __curl http://launchpadlibrarian.net/482351465/ca-certificates_20190110~12.04.1_all.deb > ca-certificates_20190110~12.04.1_all.deb && \
  __curl http://launchpadlibrarian.net/509842098/curl_7.22.0-3ubuntu4.29_amd64.deb > curl_7.22.0-3ubuntu4.29_amd64.deb && \
  __curl http://launchpadlibrarian.net/102057142/gcc-4.6-base_4.6.3-1ubuntu5_amd64.deb > gcc-4.6-base_4.6.3-1ubuntu5_amd64.deb && \
  __curl http://launchpadlibrarian.net/330397290/libasn1-8-heimdal_1.6~git20120311.dfsg.1-2ubuntu0.2_amd64.deb > libasn1-8-heimdal_1.6~git20120311.dfsg.1-2ubuntu0.2_amd64.deb && \
  __curl http://launchpadlibrarian.net/312073174/libc6_2.15-0ubuntu10.18_amd64.deb > libc6_2.15-0ubuntu10.18_amd64.deb && \
  __curl http://launchpadlibrarian.net/509842107/libcurl3_7.22.0-3ubuntu4.29_amd64.deb > libcurl3_7.22.0-3ubuntu4.29_amd64.deb && \
  __curl http://launchpadlibrarian.net/462496703/libgcrypt11_1.5.0-3ubuntu0.9_amd64.deb > libgcrypt11_1.5.0-3ubuntu0.9_amd64.deb && \
  __curl http://launchpadlibrarian.net/90920725/libgpg-error0_1.10-2ubuntu1_amd64.deb > libgpg-error0_1.10-2ubuntu1_amd64.deb && \
  __curl http://launchpadlibrarian.net/311120336/libgnutls26_2.12.14-5ubuntu3.14_amd64.deb > libgnutls26_2.12.14-5ubuntu3.14_amd64.deb && \
  __curl http://launchpadlibrarian.net/225821092/libgssapi-krb5-2_1.10+dfsg~beta1-2ubuntu0.7_amd64.deb > libgssapi-krb5-2_1.10+dfsg~beta1-2ubuntu0.7_amd64.deb && \
  __curl http://launchpadlibrarian.net/330397295/libgssapi3-heimdal_1.6~git20120311.dfsg.1-2ubuntu0.2_amd64.deb > libgssapi3-heimdal_1.6~git20120311.dfsg.1-2ubuntu0.2_amd64.deb && \
  __curl http://launchpadlibrarian.net/330397289/libheimbase1-heimdal_1.6~git20120311.dfsg.1-2ubuntu0.2_amd64.deb > libheimbase1-heimdal_1.6~git20120311.dfsg.1-2ubuntu0.2_amd64.deb && \
  __curl http://launchpadlibrarian.net/225821096/libk5crypto3_1.10+dfsg~beta1-2ubuntu0.7_amd64.deb > libk5crypto3_1.10+dfsg~beta1-2ubuntu0.7_amd64.deb && \
  __curl http://launchpadlibrarian.net/225821091/libkrb5-3_1.10+dfsg~beta1-2ubuntu0.7_amd64.deb > libkrb5-3_1.10+dfsg~beta1-2ubuntu0.7_amd64.deb && \
  __curl http://launchpadlibrarian.net/225821098/libkrb5support0_1.10+dfsg~beta1-2ubuntu0.7_amd64.deb > libkrb5support0_1.10+dfsg~beta1-2ubuntu0.7_amd64.deb && \
  __curl http://launchpadlibrarian.net/330397304/libhcrypto4-heimdal_1.6~git20120311.dfsg.1-2ubuntu0.2_amd64.deb > libhcrypto4-heimdal_1.6~git20120311.dfsg.1-2ubuntu0.2_amd64.deb && \
  __curl http://launchpadlibrarian.net/330397302/libheimntlm0-heimdal_1.6~git20120311.dfsg.1-2ubuntu0.2_amd64.deb > libheimntlm0-heimdal_1.6~git20120311.dfsg.1-2ubuntu0.2_amd64.deb && \
  __curl http://launchpadlibrarian.net/83000483/libkeyutils1_1.5.2-2_amd64.deb > libkeyutils1_1.5.2-2_amd64.deb && \
  __curl http://launchpadlibrarian.net/330397291/libkrb5-26-heimdal_1.6~git20120311.dfsg.1-2ubuntu0.2_amd64.deb > libkrb5-26-heimdal_1.6~git20120311.dfsg.1-2ubuntu0.2_amd64.deb && \
  __curl http://launchpadlibrarian.net/341213234/libidn11_1.23-2ubuntu0.2_amd64.deb > libidn11_1.23-2ubuntu0.2_amd64.deb && \
  __curl http://launchpadlibrarian.net/508006557/libldap-2.4-2_2.4.28-1.1ubuntu4.12_amd64.deb > libldap-2.4-2_2.4.28-1.1ubuntu4.12_amd64.deb && \
  __curl http://launchpadlibrarian.net/98077365/libp11-kit0_0.12-2ubuntu1_amd64.deb > libp11-kit0_0.12-2ubuntu1_amd64.deb && \
  __curl http://launchpadlibrarian.net/330397297/libroken18-heimdal_1.6~git20120311.dfsg.1-2ubuntu0.2_amd64.deb > libroken18-heimdal_1.6~git20120311.dfsg.1-2ubuntu0.2_amd64.deb && \
  __curl http://launchpadlibrarian.net/320724516/librtmp0_2.4~20110711.gitc28f1bab-1ubuntu0.1_amd64.deb > librtmp0_2.4~20110711.gitc28f1bab-1ubuntu0.1_amd64.deb && \
  __curl http://launchpadlibrarian.net/462464946/libsasl2-2_2.1.25.dfsg1-3ubuntu0.2_amd64.deb > libsasl2-2_2.1.25.dfsg1-3ubuntu0.2_amd64.deb && \
  __curl http://launchpadlibrarian.net/453600066/libsqlite3-0_3.7.9-2ubuntu1.4_amd64.deb > libsqlite3-0_3.7.9-2ubuntu1.4_amd64.deb && \
  __curl http://launchpadlibrarian.net/329563761/libtasn1-3_2.10-1ubuntu1.6_amd64.deb > libtasn1-3_2.10-1ubuntu1.6_amd64.deb && \
  __curl http://launchpadlibrarian.net/330397303/libwind0-heimdal_1.6~git20120311.dfsg.1-2ubuntu0.2_amd64.deb > libwind0-heimdal_1.6~git20120311.dfsg.1-2ubuntu0.2_amd64.deb && \
  __curl http://launchpadlibrarian.net/330397301/libhx509-5-heimdal_1.6~git20120311.dfsg.1-2ubuntu0.2_amd64.deb > libhx509-5-heimdal_1.6~git20120311.dfsg.1-2ubuntu0.2_amd64.deb && \
  __curl http://launchpadlibrarian.net/304494177/openssl_1.0.1-4ubuntu5.39_amd64.deb > openssl_1.0.1-4ubuntu5.39_amd64.deb && \
  dpkg -i *.deb && \
  rm curl.sh

# Install gcc 4.6.3
RUN curl http://launchpadlibrarian.net/102057931/gcc-4.6-base_4.6.3-1ubuntu5_i386.deb > gcc-4.6-base_4.6.3-1ubuntu5_i386.deb && \
  curl http://launchpadlibrarian.net/102057944/cpp-4.6_4.6.3-1ubuntu5_i386.deb > cpp-4.6_4.6.3-1ubuntu5_i386.deb && \
  curl http://launchpadlibrarian.net/95985360/binutils_2.22-6ubuntu1_i386.deb > binutils_2.22-6ubuntu1_i386.deb && \
  curl http://launchpadlibrarian.net/102057932/libgcc1_4.6.3-1ubuntu5_i386.deb > libgcc1_4.6.3-1ubuntu5_i386.deb && \
  curl http://launchpadlibrarian.net/102057940/libgomp1_4.6.3-1ubuntu5_i386.deb > libgomp1_4.6.3-1ubuntu5_i386.deb && \
  curl http://launchpadlibrarian.net/102057936/libquadmath0_4.6.3-1ubuntu5_i386.deb > libquadmath0_4.6.3-1ubuntu5_i386.deb && \
  curl http://launchpadlibrarian.net/312075351/libc6_2.15-0ubuntu10.18_i386.deb > libc6_2.15-0ubuntu10.18_i386.deb && \
  curl http://launchpadlibrarian.net/87459549/libgmp10_5.0.2+dfsg-2ubuntu1_i386.deb > libgmp10_5.0.2+dfsg-2ubuntu1_i386.deb && \
  curl http://launchpadlibrarian.net/83179070/libmpc2_0.9-4_i386.deb > libmpc2_0.9-4_i386.deb && \
  curl http://launchpadlibrarian.net/99920413/libmpfr4_3.1.0-3ubuntu1_i386.deb > libmpfr4_3.1.0-3ubuntu1_i386.deb && \
  curl http://launchpadlibrarian.net/84865068/zlib1g_1.2.3.4.dfsg-3ubuntu4_i386.deb > zlib1g_1.2.3.4.dfsg-3ubuntu4_i386.deb && \
  curl http://launchpadlibrarian.net/102057961/libstdc++6_4.6.3-1ubuntu5_i386.deb > libstdc++6_4.6.3-1ubuntu5_i386.deb && \
  curl http://launchpadlibrarian.net/102057975/gcc-4.6_4.6.3-1ubuntu5_i386.deb > gcc-4.6_4.6.3-1ubuntu5_i386.deb && \
  dpkg -i *.deb

# Installs clang to /workdir/clang+llvm-3.4.1-x86_64-unknown-ubuntu12.04/bin
RUN curl https://releases.llvm.org/3.4.1/clang+llvm-3.4.1-x86_64-unknown-ubuntu12.04.tar.xz > clang+llvm-3.4.1-x86_64-unknown-ubuntu12.04.tar.xz && \
  tar -xvf clang+llvm-3.4.1-x86_64-unknown-ubuntu12.04.tar.xz

RUN rm -rf *.deb *.tar.xz curl.sh
