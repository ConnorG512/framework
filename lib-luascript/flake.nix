{
  description = "Lib Lua script flake.";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs =
    { self, nixpkgs }:
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

        shellHook = "";
      };

      gcc =
        let
          pname = "luascript-lib";

          nativeInputs = with pkgs; [
            pkg-config
            cmake
            ninja
          ];
        in
        {
          gcc-debug = pkgs.stdenv.mkDerivation (finalAttrs: {
            pname = pname;
            version = "git";
            src = ./.;

            dontStrip = true;

            nativeBuildInputs = nativeInputs;
            buildInputs = [ ];
            cmakeFlags = [
              "-DCMAKE_BUILD_TYPE=Debug"

            ];
          });
          gcc-release = pkgs.stdenv.mkDerivation (finalAttrs: {
            pname = pname;
            version = "git";
            src = ./.;
            dontStrip = false;

            nativeBuildInputs = nativeInputs;
            buildInputs = [ ];
            cmakeFlags = [
              "-DCMAKE_BUILD_TYPE=Release"

            ];
          });
        };
    };
}
