

local promisse = get("url.com")
promisse.onloaded(function (request)
	local status = request.status
	local promisse2 = request.read_body()
	promisse2.onloaded(function (body)
		print("meu body")
	end)
end)