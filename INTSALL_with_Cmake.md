# Install With Cmake

```bash 
$ git clone https://github.com/long-gong/forked-minisketch.git
$ cd forked-minisketch
$ mkdir build && cd build
$ cmake ..
$ make
$ [sudo] make install
```

## Using with `vcpkg`

### [Install `vcpkg`](https://github.com/microsoft/vcpkg)

### Install with `vcpkg`
```bash
$ git clone https://github.com/long-gong/forked-minisketch.git
$ cp -r forked-minisketch/vcpkg/minisketch ~/vcpkg/ports
$ vcpkg install minisketch
```
Note that the above commands assumed that `vcpkg` is installed in the current user home directory and is added to `PATH`.

Here is a running sample:
```bash
╭─ /usr/local/vcpkg | master ?1                                                                                      1 ↵ | 3s ─╮
╰─ vcpkg install minisketch                                                                                                     ─╯
The following packages will be built and installed:
    minisketch[core]:x64-linux
Starting package 1/1: minisketch:x64-linux
Building package minisketch[core]:x64-linux...
-- Downloading https://github.com/long-gong/forked-minisketch/archive/578883fec63e0fe4d04cdac53b98e1c414bb62d2.tar.gz...
-- Extracting source /usr/local/vcpkg/downloads/long-gong-forked-minisketch-578883fec63e0fe4d04cdac53b98e1c414bb62d2.tar.gz
-- Using source at /usr/local/vcpkg/buildtrees/minisketch/src/c414bb62d2-84dde340c9
-- Configuring x64-linux-dbg
-- Configuring x64-linux-rel
-- Building x64-linux-dbg
-- Building x64-linux-rel
-- Installing: /usr/local/vcpkg/packages/minisketch_x64-linux/share/minisketch/copyright
-- Performing post-build validation
-- Performing post-build validation done
Building package minisketch[core]:x64-linux... done
Installing package minisketch[core]:x64-linux...
Installing package minisketch[core]:x64-linux... done
Elapsed time for package minisketch:x64-linux: 1.647 min

Total elapsed time: 1.647 min
```