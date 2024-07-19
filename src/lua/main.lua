
local action = input("type the action")

if action == "getbin" then
    local output = input("type the output")
	local bin = getbin(output)
	if not bin then
		print("file not found")
		exit(1)
	end
	dtw.write_file(output,bin)

elseif  action == "list_files_recursively" then
    local itens,size = list_files_recursively()
    for i=1,size do
    	print(itens[i])
    end
else
    print("invalid ection")
    exit(1)
end