from reqboost import Response, ParsedURL  # Assuming bindings expose these correctly

def test_response_initialization():
    response = Response()
    assert response.status_code == 0
    assert response._content == ""
    assert isinstance(response.headers, dict)
    assert response.url == ""
    assert isinstance(response.history, list)
    assert response.encoding == ""
    assert response.reason == ""
    assert isinstance(response.cookies, dict)
    assert response.elapsed == ""
    assert response.request == ""

def test_response_attributes():
    response = Response()
    
    response.status_code = 200
    response._content = "OK"
    response.headers = {"Content-Type": "application/json"}
    response.url = "https://example.com"
    response.encoding = "utf-8"
    response.reason = "OK"
    response.cookies = {"sessionid": "12345"}
    response.elapsed = "100ms"
    response.request = "GET / HTTP/1.1"

    assert response.status_code == 200
    assert response._content == "OK"
    assert response.headers["Content-Type"] == "application/json"
    assert response.url == "https://example.com"
    assert response.encoding == "utf-8"
    assert response.reason == "OK"
    assert response.cookies["sessionid"] == "12345"
    assert response.elapsed == "100ms"
    assert response.request == "GET / HTTP/1.1"

def test_response_repr():
    response = Response()
    response.status_code = 404
    assert repr(response) == "<Response [404]>"
