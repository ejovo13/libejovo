# _Packaging_ instructions for libejovo
#
#   This file encodes the build/installation instructions scattered throughout the
# README.md into a single nix expression.
#
#
# We start off my making a simple derivation
{pkgs ? import <nixpkgs> {}}: let
  stdenv = pkgs.stdenv;
in
  stdenv.mkDerivation {
    name = "libejovo";
    src = ./.;
    buildInputs = [pkgs.cmake pkgs.ffmpeg pkgs.pcg_c pkgs.pkg-config];

    # Manual override of different phases:
    #
    # Note:
    #   There is a "configurePhase" that get's called by a genericBuild which -
    #   at a bare minimum - calls `cmake` to configure the project.
    #
    # Additional note:
    #
    #   The "stdenv.mkDerivation" default phases are much more robust and
    #  properly set the cmakeflags to use and include files and what not.
    #  The below instructions don't actually work that well (buildPhase works if we don't touch configurePhase though...)
    #
    # #
    # configurePhase = ''
    #   echo "Configuring some stuff I guess.."
    #   echo "Running in: $(pwd)"
    #   mkdir build
    #   cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Relase -B build/ -DCMAKE_INSTALL_PREFIX=$out
    #   env
    # '';
    # #
    # buildPhase = ''
    #   echo "Wait a minute what da fuck???"
    #   echo "Current directory: $(pwd)"
    #   cd build
    #   cmake --build . -j $NIX_BUILD_CORES
    #   echo "HUH?? =============="
    # '';
    #
    # installPhase = ''
    #     # cmake --install ./
    #     # pwd
    #     # cd ../
    #     # mkdir -p $out
    #     # echo "hello" > "$out/file.txt"
    #     # pwd >> $out/file.txt
    #     mkdir -p $out
    #     ls > $out/files_in_build.txt
    #     # cmake --install .
    #     # cp -r  $out/
    # '';
  }
