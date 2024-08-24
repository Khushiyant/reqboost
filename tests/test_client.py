import reqboost

def test_client():

    # Use the Utility function to URL-encode a string
    encoded_url = reqboost.urlencode("https://example.com?query=hello world")
    assert ("https%3A%2F%2Fexample.com%3Fquery%3Dhello%20world" == encoded_url)