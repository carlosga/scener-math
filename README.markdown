# scener-math

[**scener**](http://github.com/carlosga/scener) math library (**C++ learning project**)

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

| Name                                     | Version |
|------------------------------------------|---------|
| [**CMake**](https://cmake.org/)          |         |
| [**Clang**](http://clang.llvm.org/)      | 4.0     |
| [**libC++**](http://libcxx.llvm.org/)    | 4.0     |

### Compile from Source

1. Clone repository

```
git clone --recursive https://github.com/carlosga/tvml.git
```

2. Install dependencies (packages names for Debian)

```
sudo apt-get install cmake
```

3. Configure the build (DEBUG)

```
cd tvml
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=debug -DCMAKE_CXX_COMPILER=clang++-<VERSION> -DCMAKE_C_COMPILER=clang-<VERSION>
```

4. Build

```
make -j <NUM_CORES>
```

## Running the tests

```
make test
```

## Built With

| Library/Framework                                       | Description                         |
|---------------------------------------------------------|-------------------------------------|
| [**GSL**](https://github.com/Microsoft/GSL)             | Microsoft Guideline Support Library |
| [**Google Test**](https://github.com/google/googletest) | The test runner framework           |

## Authors

* **Carlos Guzmán Álvarez** - *Initial work* - [carlosga](https://github.com/carlosga)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

## Acknowledgments

* Inspired on Nathan Reed [**'On Vector Math Libraries'**](http://www.reedbeta.com/blog/on-vector-math-libraries/) blog post
* The [template](https://gist.github.com/PurpleBooth/109311bb0361f32d87a2) this README is based on
