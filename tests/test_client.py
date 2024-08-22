import reqboost

def test_client():

    # Use the Utility function to URL-encode a string
    encoded_url = reqboost.url_encode("https://example.com?query=hello world")
    assert ("https://example.com?query=hello world" == encoded_url)