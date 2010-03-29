interfaces:
  Sample configuration for /etc/network/interfaces on Debian systems
  This file shows how to configure a bond0 device across 4 physical NICs, and then use that as the "physical" device for a bridge interface.
  This bridge device is then used by KVM for all the virtual machines.

kvm-ifup:
  Sample ifup script (/etc/kvm/kvm-ifup) that gets called everytime a KVM VM starts.
  This file uses the bridge device set in /etc/network/interfaces as the default KVM bridge.

kvm-init:
  Sample SysV-init script (/etc/init.d/kvm) for KVM.
  Create /etc/kvm/auto/ directory, and symlink config files into it (sans the .kvm).
  Any VMs listed in /etc/kvm/auto/ will be started when the host is booted, and will be stopped when the host is powered off or rebooted.
  (Based off the way /etc/xen/auto/ works.)
  Can also be used to restart all the VMs listed in the auto directory, or to get the status of all running VMs.
  Requires kvmctl.
  Uses brute-force shutdown/restart methods, which can cause data loss in the VMs.  This is really only useful for starting VMs at boot.

kvmctl:
  This is the custom management script for KVM.
  This script allows one to start, stop, or restart individual VMs, as well as connect to the console via VNC.
  This script also shows various details on the status of the VMs running on the host.

template.kvm:
  Sample configuration file.
  This is a template for creating config files for KVM VMs.  These files are used by kvmctl.
