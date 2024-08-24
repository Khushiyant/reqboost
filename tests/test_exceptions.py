import reqboost

def test_invalid_header():
    try:
        raise reqboost.InvalidHeader("Invalid header")
    except reqboost.InvalidHeader as e:
        assert str(e) == "Invalid header"
        print("Caught InvalidHeader exception:", e)

def test_invalid_proxy_url():
    try:
        raise reqboost.InvalidProxyURL("Invalid proxy URL")
    except reqboost.InvalidProxyURL as e:
        assert str(e) == "Invalid proxy URL"
        print("Caught InvalidProxyURL exception:", e)

def test_stream_consumed_error():
    try:
        raise reqboost.StreamConsumedError("Stream consumed")
    except reqboost.StreamConsumedError as e:
        assert str(e) == "Stream consumed"
        print("Caught StreamConsumedError exception:", e)