{
  description = "Logger lib flake.";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { self, nixpkgs }: 
  let
    pkgs = nixpkgs.legacyPackages.x86_64-linux;
  in 
  {
    devShells.x86_64-linux.default = pkgs.mkShell {
      packages = with pkgs; [ 
        clang-tools
        cmake 
        pkg-config
        ninja
      ];

      shellHook = ''
      '';
    };
    
    packages.x86_64-linux = 
    {
      gcc-debug = pkgs.stdenv.mkDerivation (finalAttrs: {
        pname = "logger-lib";
        version = "git";
        src = ./.;

        dontStrip = true;

        nativeBuildInputs = [ ];
        buildInputs = [ ];
        cmakeFlags = [
          "-DCMAKE_BUILD_TYPE=Debug"
          
        ];
      });
    };
  };
}
