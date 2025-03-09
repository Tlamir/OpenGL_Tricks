# OpenGL Tricks

A simple OpenGL project built to understand and practice computer graphics.

## Overview

This project is a Visual Studio solution demonstrating fundamental OpenGL concepts, including:

- Setting up a rendering window using GLFW
- Creating and managing vertex buffers
- Working with index buffers for efficient rendering
- Implementing shader programs
- Handling vertex attributes
- Creating vertex arrays
- Using uniforms to pass data from CPU to GPU

## Requirements

- Visual Studio (2019 or newer recommended)
- OpenGL libraries:
  - GLEW
  - GLFW

## Getting Started

1. Clone this repository
2. Open the solution in Visual Studio
3. Build and run the project

## Project Structure

The project includes several custom classes to abstract OpenGL functionality:
- `Renderer` - Handles drawing operations
- `VertexBuffer` - Manages vertex data in GPU memory
- `IndexBuffer` - Manages indices for efficient geometry rendering
- `VertexArray` - Organizes vertex attribute configurations
- `Shader` - Loads, compiles, and manages shader programs

## Learning Resources

This project is intended for educational purposes to learn graphics programming concepts with OpenGL. It demonstrates the OpenGL rendering pipeline, shader programming, and basic computer graphics principles.

## Notes

- This is a learning project, not intended for production use
- The code includes helpful comments explaining key OpenGL concepts
- The project uses modern OpenGL (Core Profile) rather than legacy OpenGL