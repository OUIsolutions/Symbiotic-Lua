
local action = input("type the action")

if action == "getbin" then
    local output = input("type the output")
	local bin = getbin(output)
	if not bin then
		print("file not found")
		exit(1)
	end
	dtw.write_file(output,bin)
end