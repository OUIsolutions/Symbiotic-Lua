
function get_number(msg)
    local user_input = input(msg)
    local converted = tonumber(user_input)
    if converted == nil then
        print("value its not a number")
        exit(1)
    end
    return converted
 end
local num1 = get_number("type the first num:")
local num2 = get_number("type the second number:")
local operator = input("type the operator(+-*/):")

if operator == "+" then
    print("the result its: ",add(num1,num2))

elseif operator == "-" then
    print("the result its: ",sub(num1,num2))

elseif operator == "*" then
    print("the result its: ",mul(num1,num2))

elseif operator == "/" then
    print("the result its: ",div(num1,num2))

else
    print("invalid operator")
    exit(1)
end

