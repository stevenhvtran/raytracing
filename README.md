# Ray Tracing
Based on the book [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
For the theory behind the renders and example code, see the link above.

## Pretty Renders I've Made
- The first render output, in a `.ppm` file
  - `.ppm` files store `RGB` values that go from left to right, top to bottom
  - This image has a constant blue value, red increases from left-right, green decreases from top-bottom  
  !['Basic render'](./renders_png/image2.png)
- A simple gradient
  - By ray-tracing, we can pick a value for each pixel by getting the y-component of the direction vector of the ray
  - We can colour this with more "blue" the higher up the ray points  
  !['Gradient'](./renders_png/lerp.png)
- A circle (a sphere?)
  - We can render objects on the screen too by adding objects to the 3D environment
  - If we add a sphere to the environment, we can change the colour of pixels depending on if the ray intersects with the 3D object
  - We can also add an outline by checking if the intersection is near the edge
  - The result is a circle that represents a sphere
  !['Circle'](./renders_png/sphere_collision_outline.png)
- Normals colouring
  - We can give this sphere a bit more character by colouring it
  - One approach is to map the normal vector at the point of collision between the ray and the sphere's surface to a colour  
  !['Coloured sphere'](./renders_png/colourful_sphere.png)
- More spheres
  - We can abstract the sphere object and render more spheres
  - Here's 3 spheres on top of a big sphere:
  !['More spheres'](./renders_png/focal_length.png)
- Anti-Aliasing
  - We can fix the jagged edges of the sphere by tracing more rays per pixel
  - We pick points close to the ray and average them together to generate anti-aliased renders
  - Light AA (Not as many rays per pixel):
    !['Light AA'](./renders_png/light_aa_spheres.png)
  - Medium AA (More rays per pixel, smoother):
    !['Medium AA'](./renders_png/medium_aa_spheres.png)
  - Heavy AA (Even more rays per pixel, almost blurry edges):
    !['Heavy AA'](./renders_png/heavy_aa_spheres.png)
- Diffuse materials
  - We can model light bounces from our spheres to simulate light in real life
  - For diffuse materials, light bounces randomly with a probability distribution, generating a "matte" look
  - We simulate multiple light bounces per pixel and average them out to get this:
  !['Diffuse spheres'](./renders_png/diffuse_sphere.png)
  - Gamma correction can be applied to correct the overly dark spheres:
    !['Gamma correction'](./renders_png/gamma_corrected_diffuse_sphere.png)
  - We can also use different probability distributions to model light bounces
  - Heres a lambertian reflectance sphere:
    !['Lambertian'](./renders_png/lambertian_sphere.png)
    - Note: At this point a slight error is made in my renders where the co-ordinate system of the shadows is slightly off, leading to left-skewing shadows
      - This is fixed later on
- Metals
  - Metals reflect light in a more direct way, we can trace these reflected rays to get metals now  
  !['Metals'](./renders_png/shadow_debug6.png)
  - We can also make metals that aren't fully reflective by only reflecting rays directly some of the time, and reflecting them randomly other times
    !['Fuzzy Metal'](./renders_png/fuzzy_metal.png)
- Glass
  - We can use light refraction properties to generate spheres that exhibit glass-like behaviour too
  !['Glass sphere'](./renders_png/schlick_approx_dielectric_spheres.png)
  - We can also render hollow spheres:
    !['Hollow sphere'](./renders_png/hollow_sphere.png)
