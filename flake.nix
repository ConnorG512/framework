{
  description = "Game Framework top level flake.";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    libFilesystem.url = "path:./lib-filesystem";
    libLogger.url = "path:./lib-logger";
    libLuascript.url = "path:./lib-luascript";
  };

  outputs = { self, nixpkgs, libFilesystem, libLogger, libLuascript }: 
  let
    pkgs = nixpkgs.legacyPackages.x86_64-linux;
  in 
  {
    devShells.x86_64-linux.default = pkgs.mkShell {
      inputsFrom = [
        libFilesystem.devShells.x86_64-linux.default
        libLogger.devShells.x86_64-linux.default
      ];

      shellHook = ''
        echo "Entering top level shell!"
      '';
    };

    packages.x86_64-linux.bundle = pkgs.symlinkJoin {
      name = "libraries-debug";
      paths = [
        libFilesystem.packages.x86_64-linux.gcc-debug
        libLogger.packages.x86_64-linux.gcc-debug
        #libLuascript.packages.x86_64-linux.gcc-debug
      ];
    };
  };
}
