local elements, size = bin.list_files_recursively("cars/")

for i = 1, size do
    print(elements[i])
end
