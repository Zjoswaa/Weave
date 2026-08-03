{
  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs { inherit system; };
    in {
      devShells.${system}.default = pkgs.mkShell {
        # nativeBuildInputs = with pkgs; [ cmake pkg-config wayland ];
        buildInputs = with pkgs; [
          libx11 libxrandr libxinerama
          libxcursor libxi libxext
          libGL
          wayland
          wayland-scanner wayland-protocols libxkbcommon
          libffi
        ];

	shellHook = ''
          export LD_LIBRARY_PATH=${pkgs.lib.makeLibraryPath (with pkgs; [
            wayland
            libGL
            libxkbcommon
          ])}:$LD_LIBRARY_PATH
        '';
      };
    };
}
