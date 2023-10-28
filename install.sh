echo "Installing Rust"
curl https://sh.rustup.rs -sSf | sh -s -- -y
source "$HOME/.cargo/env"

echo "Downloading checker"
cargo install checker-tema-3-sd

ln -s ~/.cargo/bin/checker-tema-3-sd .
mv checker-tema-3-sd check

echo "Install finished. Good luck!"
