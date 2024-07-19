
local action = getargv(1)
if action == nil then
	print("action must be provided\n")
	exit(1)
end

if action == "write" then
    local binpath  = getargv(2)
	if binpath == nil then
        print("bin path must be provided\n")
        exit(1)
	end
    local output = getargv(3)
    if output == nil then
        print("output path must be provided\n")
        exit(1)
    end


	local isfile = bin.isfile(binpath)
	local isfodler = bin.isdir(binpath)

    if not isfile and not isfodler then
    	 print("bin path "..binpath.." not exit\n")
         exit(1)
    end
    if isfile then
        dtw.write_file(output,bin.getbin(binpath))
	end

    if isfodler then
    	local itens,size = bin.list_files_recursively(binpath)
    	for i=0,size do
    	      local old_path = itens[i]
              local path = dtw.newPath(itens[i]);
              path.remove_sub_dir_at_index(0)
              path.add_start_dir(binpath)
              print(path.get_full_path())
              dtw.write_file(path,bin.getbin(old_path))
    	end
    end

elseif  action == "list" then
    local path = getargv(2)

    local itens,size = bin.list_files_recursively(path)
    for i=1,size do
    	print(itens[i].."\n")
    end
else
    print("invalid action")
    exit(1)
end

