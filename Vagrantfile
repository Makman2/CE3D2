# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure(2) do |config|
    config.vm.box = "bento/fedora-23"
    config.vm.provider "virtualbox"

    config.vm.provision "shell", inline: <<-SHELL
        sudo dnf update -y
        sudo dnf install -y gcc gcc-c++ boost boost-devel doxygen cmake
    SHELL
end
