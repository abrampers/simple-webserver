from locust import HttpLocust, TaskSet, task


class TestingSet(TaskSet):
    @task(1)
    def index(self):
        self.client.get("/")


class WebsiteUser(HttpLocust):
    task_set = TestingSet
    min_wait = 5000
    max_wait = 9000
