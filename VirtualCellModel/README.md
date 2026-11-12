# Virtual Cell Model (VCM)

## About the Project

The **Virtual Cell Model (VCM)** is a molecular dynamics simulation software package developed by Dr. Ali Farnudi and collaborators.

The main idea behind VCM is to represent a physical system as a collection of particles, calculate the forces and potentials between them, and use Newton's equations of motion to simulate how the system evolves over time.

VCM is designed to work with different types of particle-based structures:

- **Linear chains:** Used to represent polymers and other chain-like structures.
- **2D triangular meshes:** Used to model membranes and vesicles.
- **3D meshes:** Used to represent solid objects and more complex structures.

These structures can also be combined to build more complex systems for computational modelling and simulation.

VCM uses **OpenMM** as its molecular dynamics engine, allowing simulations to take advantage of available computational resources, including multiple CPU cores and GPUs.

## Background

My interest in VCM comes from its application to computational biophysics and the mechanical behaviour of biological systems. The work of Dr. Farnudi provides a framework for representing cellular structures and studying their dynamics through particle-based simulations.

## Installation

### Requirements

Before building the project, install:

- [OpenMM](https://openmm.org/)
- [Boost](https://www.boost.org/)

### Build from source

1. Clone the repository:

```bash
git clone <repository-url>
```

2. Enter the project directory:

```bash
cd VirtualCellModel
```

3. Build the project:

```bash
make -j4
```

For more detailed installation instructions, see the [VCM installation guide](https://afarnudi.github.io/VirtualCellModel/md__doxygen__installation.html).

## Documentation

For more information about the software, its structure, and its available features, visit:

- [Virtual Cell Model documentation](https://afarnudi.github.io/VirtualCellModel/index.html)
- [Installation guide](https://afarnudi.github.io/VirtualCellModel/md__doxygen__installation.html)

## References

The original Virtual Cell Model software and its documentation are associated with the work of Dr. Ali Farnudi and collaborators.
