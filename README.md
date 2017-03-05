# Design and Analysis of Algorithms
# RAM Machine Simulator
## By Adrián Rodríguez Bazaga
### Contact email: adrian@qmindgroup.com

# Dependencies

```sh
$ sudo apt-get install build-essential 
```
Uses *C++11*

# Build Status
![](http://i.imgur.com/7gvWrxI.png?1)

# How to compile?
Use make inside the /src/ directory. Compilation uses dynamic linking, so only classes that have changed will be compiled, the others will be linked using the object (.o) that's inside ./obj/ directory.
```sh
$ make clean
$ make
```


# How to execute?
The result of the compilation is placed inside /src/compiled folder, with the name RAMmachine, to execute it just use ./src/compiled/RAMmachine from the root directory

# Download source code

```sh
$ git clone https://github.com/AdrianBZG/RAM-Machine-Simulator.git
```

# Documentation

Take a look at the documentation by clicking [here](http://adrianbzg.github.io/RAM-Machine-Simulator/html/).

LICENSE
=======
``` java
Copyright 2016 Adrián Rodríguez Bazaga

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
```
