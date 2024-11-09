{
  description = "Flake for `nm-net-strongest`";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    {
      self,
      nixpkgs,
      flake-utils,
    }:
    let
      systems = [
        "x86_64-linux"
        "aarch64-linux"
      ];
    in
    flake-utils.lib.eachSystem systems (
      system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in
      with pkgs;
      {
        packages = rec {
          nm-net-strongest = stdenv.mkDerivation {
            name = "nm-net-strongest";
            version = "0.1.0";
            src = ./.;
            nativeBuildInputs = [
              meson
              ninja
              pkg-config
              clang-tools
              clang-analyzer
            ];
            buildInputs = [
              networkmanager.dev
              glib
            ];
          };
          default = nm-net-strongest;
        };

        apps = rec {
          nm-net-strongest = flake-utils.lib.mkApp {
            drv = self.packages.${system}.nm-net-strongest;
            name = "nm-net-strongest";
          };
          default = nm-net-strongest;
        };

        devShells.default = mkShell {
          name = "nm-net-strongest";
          buildInputs = [
            self.packages.${system}.nm-net-strongest.nativeBuildInputs
            self.packages.${system}.nm-net-strongest.buildInputs
          ];
        };
      }
    );
}
