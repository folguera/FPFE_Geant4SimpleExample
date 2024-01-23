import uproot
import pandas as pd
import matplotlib.pyplot as plt

# Read the root file into a pandas DataFrame
flat_tree = uproot.open("B4d_build/B4_90MeV.root")['B4']
print(flat_tree.keys())

# Get the list of variables/columns in the DataFrame
df = flat_tree.arrays(library="pd")
print(df)

# Draw each variable
for variable in df.columns:
    plt.figure()
    plt.hist(df[variable], bins=50)
    plt.xlabel(variable)
    plt.ylabel('Count')
    plt.title(f'Histogram of {variable}')
    plt.show()
