{
  description = "Flake for libejovo C library";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = {
    self,
    nixpkgs,
  }: let
    pkgs = import nixpkgs {system = "x86_64-linux";};
  in {
    packages.x86_64-linux.default = import ./default.nix {
      pkgs = pkgs;
    };
    devShells.x86_64-linux.default = pkgs.mkShell {
      buildInputs = [pkgs.ffmpeg pkgs.cmake pkgs.pcg_c pkgs.pkg-config];

      shellHook = ''
        fish -c echo "ffmpeg is available at $(which ffmpeg)"
      '';
    };
  };
}
