# Build and push

```bash
docker build -t nicolalovo/os:latest .
docker push nicolalovo/os:latest
```

# Pull and run

## Pull container

```bash
docker pull nicolalovo/os:latest
```

## Run container for the first time

```bash
docker run -it nicolalovo/os:latest
```

### Exit from container

```bash
exit
```

## Stop container

```bash
docker stop <container_id>
```

## Run container after first time

### Get container id

```bash
docker container ps
```

Example output:

```
CONTAINER ID   IMAGE                  COMMAND       CREATED         STATUS         PORTS     NAMES
3f454b9bfbc0   nicolalovo/os:latest   "/bin/bash"   4 seconds ago   Up 4 seconds             xenodochial_elion
```

In this case, the container id is `3f454b9bfbc0`.

## Restart container

```bash
docker start -i <container_id>
```

## Create a shell in started container

```bash
docker exec -it <container_id> /bin/bash
```
