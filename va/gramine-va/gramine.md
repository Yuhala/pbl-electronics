## How to setup and use Gramine for the project
- Supported OS: Ubuntu 20.04 LTS and Ubuntu 22.04 LTS

- Run `install-gramine.sh` script.
- Generate enclave signing key. Generated key is stored in `$HOME/.config/gramine/enclave-key.pem`
```
gramine-sgx-gen-private-key
```

- Clone Gramine repo containing example code.
```
git clone --depth 1 --branch v1.2 https://github.com/gramineproject/gramine.git
```
- Cd to `helloworld` example directory.
```
cd gramine/CI-Examples/helloworld
```
- Modify `helloworld.manifest.template` to match the one in this folder.
- Build and run without SGX.
```
make
gramine-direct helloworld
```
- Build and run with SGX.
```
make SGX=1
gramine-sgx helloworld
```

## Gramine shielded containers
- Install prerequisites.
```
sudo apt-get install docker.io python3 python3-pip
pip3 install docker jinja2 tomli tomli-w pyyaml
```

- Add user to docker group.
```
sudo groupadd docker
sudo gpasswd -a $USER docker
sudo chmod 666 /var/run/docker.sock #Ubuntu 20.04
```
- Do reboot if sudo still required after above configs.
- Test docker with hello-world.
```
docker pull hello-world 
docker run --rm hello-world
```
- List docker images.
```
docker image ls
```
- List docker containers.
```
docker ps -a 
```
- Stop and remove all docker containers.
```
docker stop $(docker ps -a -q) # stop all containers
docker rm $(docker ps -a -q) # remove 
```
- Build base image for application.
```
docker build -t hello-world-gramine .
```
- In case you need to delete the docker image.
```
sudo docker rmi hello-world-gramine:latest #change the last value to fit the image id
```
- Run container 
```
docker run --rm hello-world-gramine
```
## Creating and running GSC 
- - Build base image for application.
```
docker build -t hello-world-gramine .
```
- Clone `GSC` repository containing `gsc` tool.
```
git clone https://github.com/gramineproject/gsc.git
```
- Create config file
```
cd gsc
cp config.yaml.template config.yaml
```
- If using OOT driver, enclave token may be needed.
```
gramine-sgx-get-token --sig helloworld.sig -o helloworld.token
```
- Graminize docker image
- Make sure to use the `--no-cache` option to prevent the build from using stale config files.
```
./gsc build --insecure-args hello-world-gramine /path/to/helloworld.manifest -c /path/to/config.yaml
./gsc build --insecure-args --no-cache cpc-gramine docker-cpc/cpc.manifest -c config.yaml
```
- Sign graminized image
```
./gsc sign-image hello-world-gramine $HOME/.config/gramine/enclave-key.pem 
./gsc sign-image cpc-gramine $HOME/.config/gramine/enclave-key.pem
```
- Run graminized image
```
docker run --rm --device=/dev/sgx_enclave -v /var/run/aesmd/aesm.socket:/var/run/aesmd/aesm.socket gsc-hello-world-gramine 
```

## CPC docker container + shared memory
- Build `worker` with `make`.
- Build normal (non-gramine) `docker-cpc` image.
```
docker build -t docker-cpc .
```
- Run `worker`, then run `docker-cpc` container.
- Running container with access to shared memory
```
docker run --rm --ipc=host docker-cpc
docker run --rm -it --privileged --shm-size=16m --device=/dev/sgx_enclave -v /var/run/aesmd/aesm.socket:/var/run/aesmd/aesm.socket -v /dev/shm:/dev/shm <container-name>

```

## Graminize `docker-cpc` image
- Graminize image
```
./gsc build --insecure-args docker-cpc docker-cpc/cpc.manifest -c config.yaml
```
- Sign graminized image
```
./gsc sign-image docker-cpc $HOME/.config/gramine/enclave-key.pem 
```
- Run graminized image
```
docker run --rm --privileged --ipc=host --device=/dev/sgx_enclave -v /var/run/aesmd/aesm.socket:/var/run/aesmd/aesm.socket -v /cpc_shared_memory:/cpc_shared_memory -v /dev/shm/cpc_shared_memory:/dev/shm/cpc_shared_memory gsc-docker-cpc
```
## Running entire application inside container
- 
```
docker run --rm --ipc=host --device=/dev/sgx_enclave -v /var/run/aesmd/aesm.socket:/var/run/aesmd/aesm.socket gsc-alone-cpc
```


