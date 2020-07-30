CMS analysis software setup
===========================


# Main links

- http://opendata.cern.ch/docs/cms-guide-for-research
- https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuide



# CMSSW using Docker

Standard instructions can be found at:

http://opendata.cern.ch/docs/cms-guide-docker

The link fails to provide a fully working GUI interface with macOS X. To achieve
that, we need to connect the Docker Container to XQuartz via `socat` using TCP
listen when invoking `docker run`.

```
$ brew install socat
$ socat TCP-LISTEN:6000,reuseaddr,fork UNIX-CLIENT:\"$DISPLAY\" &
$ docker run -e DISPLAY=$(ipconfig getifaddr en0):0 [optional: --rm] --name cms-opendata -it cmsopendata/cmssw_5_3_32 /bin/bash
```

**CMMSW should be up and running. The ROOT splash screen should appear upon
opening it.**

Restarting the `cms-opendata` container in case the `--rm` flag was not used:

```
$ docker start -i cms-opendata
```

Setting up a function in `.bash_profile` makes life easier:

```
# CMSSW
function cmssw {
  socat TCP-LISTEN:6000,reuseaddr,fork UNIX-CLIENT:\"$DISPLAY\" &
  socatPID=$!

  docker start -i cms-opendata

  kill -15 $socatPID
}
```



# Setting up CMSSW

The Docker Container should start up in a `src` dir. Invoking `cmsenv` will
set up, you guessed it, the cms environment.

```
[00:00:00] cmsusr@blah ~/CMSSW_5_3_32/src $ cmsenv
```
[INCOMPLETE]




# Using open-data ROOT files

[INCOMPLETE]
