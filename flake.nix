{
  description = "Game Framework top level flake.";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    libFilesystem.url = "path:./lib-filesystem";
  };

  outputs = { self, nixpkgs, libFilesystem }: 
  let
    pkgs = nixpkgs.legacyPackages.x86_64-linux;
  in 
  {
    devShells.x86_64-linux.default = pkgs.mkShell {
      inputsFrom = [
        libFilesystem.devShells.x86_64-linux.default
      ];

      shellHook = ''
        echo "Entering top level shell!"
      '';
    };
  };
}
