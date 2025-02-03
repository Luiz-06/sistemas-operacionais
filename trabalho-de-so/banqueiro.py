class BankersAlgorithm:
    def __init__(self, num_processes, num_resources, max_matrix, allocation_matrix, available_resources):
        self.num_processes = num_processes
        self.num_resources = num_resources
        self.max_matrix = max_matrix
        self.allocation_matrix = allocation_matrix
        self.available_resources = available_resources
        
        self.need_matrix = [
            [self.max_matrix[i][j] - self.allocation_matrix[i][j] 
             for j in range(num_resources)] 
            for i in range(num_processes)
        ]
    
    def is_safe_state(self):
        work = self.available_resources.copy()
        finish = [False] * self.num_processes
        safe_sequence = []
        
        for _ in range(self.num_processes):
            found = False
            
            for p in range(self.num_processes):
                if not finish[p] and all(self.need_matrix[p][j] <= work[j] for j in range(self.num_resources)):
                    for j in range(self.num_resources):
                        work[j] += self.allocation_matrix[p][j]
                    
                    finish[p] = True
                    safe_sequence.append(p)
                    found = True
                    break
            
            if not found:
                return False, []
        
        return True, safe_sequence
    
    def request_resources(self, process_id, request):
        if any(request[j] > self.need_matrix[process_id][j] for j in range(self.num_resources)):
            raise ValueError("Request exceeds maximum need")
        
        if any(request[j] > self.available_resources[j] for j in range(self.num_resources)):
            return False
        
        for j in range(self.num_resources):
            self.available_resources[j] -= request[j]
            self.allocation_matrix[process_id][j] += request[j]
            self.need_matrix[process_id][j] -= request[j]
        
        is_safe, _ = self.is_safe_state()
        
        if not is_safe:
            for j in range(self.num_resources):
                self.available_resources[j] += request[j]
                self.allocation_matrix[process_id][j] -= request[j]
                self.need_matrix[process_id][j] += request[j]
            return False
        
        return True

def main():
    print("Test Case 1: Safe State Scenario")
    num_processes = 5
    num_resources = 3
    
    max_matrix = [
        [7, 5, 3],
        [3, 2, 2],
        [9, 0, 2],
        [2, 2, 2],
        [4, 3, 3]
    ]
    
    allocation_matrix = [
        [0, 1, 0],
        [2, 0, 0],
        [3, 0, 2],
        [2, 1, 1],
        [0, 0, 2]
    ]
    
    available_resources = [3, 3, 2]
    
    banker = BankersAlgorithm(num_processes, num_resources, max_matrix, allocation_matrix, available_resources)
    
    is_safe, safe_sequence = banker.is_safe_state()
    print(f"Is Safe State: {is_safe}")
    print(f"Safe Sequence: {safe_sequence}")
    
    test_request = [1, 0, 2]
    print("\nTesting Resource Request:")
    request_result = banker.request_resources(0, test_request)
    print(f"Request Granted: {request_result}")
    
    print("\nTest Case 2: Unsafe State Scenario")
    max_matrix_unsafe = [
        [6, 4, 3],
        [3, 2, 2],
        [9, 0, 2],
        [2, 2, 2],
        [4, 3, 3]
    ]
    
    allocation_matrix_unsafe = [
        [0, 1, 0],
        [3, 0, 2],
        [3, 0, 2],
        [2, 1, 1],
        [0, 0, 2]
    ]
    
    available_resources_unsafe = [1, 1, 0]
    
    banker_unsafe = BankersAlgorithm(num_processes, num_resources, 
                                     max_matrix_unsafe, 
                                     allocation_matrix_unsafe, 
                                     available_resources_unsafe)
    
    is_safe_unsafe, safe_sequence_unsafe = banker_unsafe.is_safe_state()
    print(f"Is Safe State: {is_safe_unsafe}")
    print(f"Safe Sequence: {safe_sequence_unsafe}")

if __name__ == "__main__":
    main()