import './App.css';
import 'bootstrap/dist/css/bootstrap.min.css';
import Dropdown from 'react-bootstrap/Dropdown';
import DropdownButton from 'react-bootstrap/DropdownButton';
import logo from './Hash.webp';
import React, { useState } from 'react';
import axios from 'axios';

// specific text style for input text
const labelInput = {
  fontFamily: '"Jersey 10", sans-serif',
  fontSize: "20px",
  color: "#FFFFFF",
  letterSpacing: "3px",
};

// visualize the min heap
const visualizeMinHeap = (arr, index = 0, position = 0, level = 0) => {
  // if min heap empty, return nothing
  if(index >= arr.length){
    return null;
  }

  // get positions for children of current node
  const left = (2 * index) + 1;
  const right = (2 * index) + 2;

  const spacing = 200 / (level + 1);

  return (
    // display current node
    <div>
      <div style={{ position: 'relative', marginLeft: position}}>
        <div
          style={{
            width: 50,
            height: 50,
            backgroundColor: '#FFFFFF',
            color: 'black',
            textAlign: 'center',
            lineHeight: '50px',
            borderRadius: '50%',
          }}>
          {arr[index]}
        </div>
      </div>

      {/* display children nodes recursively*/}
      <div style={{ display: 'flex' }}>
        {visualizeMinHeap(arr, left, position - spacing, level + 1)}
        {visualizeMinHeap(arr, right, position + spacing, level + 1)}
      </div>
    </div>
  );
};

function App() {

  // create variable to hold user input
  const [user_input, setInput] = useState('');

  // test visualization of a min heap
  const arr = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14];
  
  // axios post functionality from: https://www.geeksforgeeks.org/axios-in-react-a-guide-for-beginners/#post-request-with-axios
  const handleChange = (event) => {
    setInput(event.target.value);
  }
  const handleClick = (event) => {
    event.preventDefault();
    
    axios.post('http://localhost:1000/proj3', {data: user_input})
    .then((response) => {
      console.log(response); 
      console.log(response.data)
    });
  };

  // actual function and displays for the website
  return (
    <div className="App">
      <header className="App-header">

        {/*project image*/}
        <img src={logo} className="App-logo" alt="logo" />

        {/*title*/}
        <p>
          Financial Trend Analyzer
        </p>

        {/*dropdown menu info and functionality from https://react-bootstrap.netlify.app/docs/components/dropdowns/*/}
        <DropdownButton id="dropdown-basic-button" title="Select from options below">
          <Dropdown.Item>
            2022
          </Dropdown.Item>
          <Dropdown.Item>
            2023
          </Dropdown.Item>
        </DropdownButton>

        {/*text box to take in user input*/}
        <div style={{ ...labelInput, marginTop: "20px", marginBottom: "30px" }}>
          Input Range:
          <div
            style={{ ...labelInput, marginTop: "10px", marginBottom: "10px" }}>
            <input
              type="text"
              value={user_input}
              onChange={(e) => setInput(e.target.value)}
              style={{
                fontFamily: '"Jersey 10", sans-serif',
                fontSize: "20px",
                padding: "5px",
                borderRadius: "4px",
                border: "1px solid #ccc",
              }}
            />
          </div>
      </div>

      {/*visualize text box for user input and submit button to send info to backend*/}
      <div>
        <form onSubmit={handleClick}>
          <label>
            Submit User Input
            <input
              type="text"
              name="user_input"
              value={user_input}
              onChange={handleChange}
            />
          </label>
          <button type="Submit">
            Test
          </button>
        </form>
      </div>

      {/*visualize the min heap*/}
      <div style={{marginTop: '50px'}}>
        {visualizeMinHeap(arr)}
      </div>

      </header>
    </div>
  );
}

export default App;
