#!/usr/bin/env python
# coding: utf-8

# In[2]:


import pyvista as pv

# Load the .vtk file
filename = 'square1156.vtk'
mesh = pv.read(filename)

# Create a plotter object
plotter = pv.Plotter()

# Add the mesh to the plotter
plotter.add_mesh(mesh, show_edges=True)

# Set the camera position to the top view
plotter.view_xy()

# Save the screenshot with higher resolution
screenshot_path = 'top_view_vtk1156.png'
plotter.screenshot(screenshot_path, window_size=[1600, 1200])  # Increase window size for higher resolution

# Close the plotter
plotter.close()


# In[ ]:





# In[ ]:




