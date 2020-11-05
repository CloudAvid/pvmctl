# Introduction
**_pvmctl_**, part of PVM-Prototype, is a set of scripts and schemes to manage virtual machines based on KVM.

**_pvmctl_** is part of PVM-prototype, our early try to write special hypervisor based on KVM named **_PVM_**. 

**_pvmctl_** has been developed based on early versions of [kvmctl](http://www.linux-kvm.org/page/HowToConfigScript).

By **_pvmctl_** user could manage virtual-machines based on KVM. use **_pvmctl help_** to see pvmctl abilities. 
Read [Project wiki](https://github.com/CloudAvid/pvmctl/wiki) for more information.

**_pvmctl_** has a wraper for cluster environment named [pcad](https://github.com/CloudAvid/pcad) to achive abilities like of HA.

# Installation

Run **_install-pvmctl_** for installation:
```shell
$ ./install-pvmctl
```

# Documentation

Complete tutorial located at [Project wiki](https://github.com/CloudAvid/pvmctl/wiki).

See also **_pvmctl help_**:
```shell
pvmctl is a management and control script for KVM-based virtual machines.

Usage:  pvmctl start    host    - start the named VM

        pvmctl shutdown host    - send shutdown signal to VM
        pvmctl reset    host    - send reset signal to VM

        pvmctl stop     host    - stop  the named VM (only use if the guest is hung)
        pvmctl restart  host    - stop and then start the named VM (only use if the guest is hung)

        pvmctl status           - show the names of all running VMs
        pvmctl status   kvm     - show full details for all running kvm processes
        pvmctl status   host    - show full details for the named kvm process

        pvmctl mkimg    host image_name image_size  - create a disk image
        pvmctl rmimg    host image_name             - remove disk image of the host
        pvmctl rnimg    host image_name new_name    - rename disk image of the host
        pvmctl resize   host image_index size[K|M|G]- resize disk image of the host

        pvmctl new      host_name sid               - Create A virtual machine
        pvmctl create   template host_name sid      - Create A virtual machine from template
        pvmctl clone    host clone_name [new_sid]   - creating a clone from the host

        pvmctl rename   host new_name               - rename host to new_name
        pvmctl rmvm     host                        - delete virtual machine
        pvmctl mvvm     host new_sid                - move virtual machine to new storage

        pvmctl edit     host                        - open config file for edit
        pvmctl info     host                        - print out host information (parameters in config file)
        pvmctl chcdrom  host cdrom# iso             - change cdrom for running machines

        pvmctl mktmpl   host  [template_name]       - Create A virtual Template from host
        pvmctl rmtmpl   template_name               - Remove the Virtual Template
        pvmctl mkiso    iso_name                    - Create An ISO image from the CD in Local CDROM(local)
        pvmctl rmiso    iso_name                    - Remove the ISO image

        pvmctl snaps    host                        - show all snapshots of the host
        pvmctl mksnap   host  [tag|id]              - make an snapshot with [tag|id] if given, or not a new
        pvmctl ldsnap   host   tag|id               - load snapshot with tag|id
        pvmctl rmsnap   host   tag|id               - remove snapshot with tag|id

        pvmctl ls                                   - print out list of virtual machines
        pvmctl lst                                  - print out list of Virtual Templates
        pvmctl lscd                                 - print out list of CD Images (ISO files)
        pvmctl lsid                                 - print out list of Virtual Storages.

        pvmctl loadvsws                             - load virtual switches and add them to local system.

        pvmctl help                                 - show this usage
```

# Contributing Code
If you are capable of contributing code changes, we encourage you to do so. You can help us in different fields:
* Develop new features
* Improving Documentation
* ... 

# Bugs
 Please use github [issues](https://github.com/CloudAvid/pvmctl/issues) to report bugs. 
# About
Copyright 2010-2020 [CloudAvid](https://www.cloudavid.com).
