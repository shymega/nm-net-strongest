# Copyright 2019-2024 Dom Rodriguez (shymega)
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#
# See the License for the specific language governing permissions and
# limitations under the License.

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
            meta = with lib; rec {
              maintainers = [ shymega ];
              mainProgram = "nm-net-strongest";
            };
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
