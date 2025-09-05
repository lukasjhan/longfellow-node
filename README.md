# Longfellow Node.js Wrapper

## Build

1. Build and Install Longfellow

1.1 prerequisites (ubuntu)

```bash
sudo apt-get update
sudo apt-get install -y libssl-dev libzstd-dev libgtest-dev libbenchmark-dev zlib1g-dev clang cmake

```

```bash
git submodule update --init --recursive
cd third_party/longfellow-zk

# Build and install Longfellow
CXX=clang++ cmake -S lib -B build -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=$PWD/install
cmake --build build -j
cmake --install build
```

2. Build and Install Longfellow Node.js Wrapper (project root directory)

```bash
pnpm install
pnpm configure
pnpm build
```

3. Test

```bash
pnpm test
```
